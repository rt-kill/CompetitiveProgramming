#include <bits/stdc++.h>

using namespace std;


template<typename Input, typename Output>/*{{{*/
class AbstractValues
{
protected:
    using Input_t = Input;
    using Output_t = Output;

    vector<Input>  inputs;
    vector<Output> outputs;
};/*}}}*/

// anything with points that can filter out outliars
template<typename Values>/*{{{*/
class AbstractFilter : public virtual Values
{
protected:
    static_assert( is_base_of<AbstractValues<
                        typename Values::Input_t,
                        typename Values::Output_t
                   >, Values>::value );

public:
    virtual void applyFilter() = 0;
};/*}}}*/

// anything with points that can evalutate some input with respect to them
template<typename Values>/*{{{*/
class AbstractModel : public virtual Values
{
protected:
    static_assert( is_base_of<AbstractValues<
                        typename Values::Input_t,
                        typename Values::Output_t
                   >, Values>::value );

public:
    virtual typename Values::Output_t applyModel( typename Values::Input_t input ) = 0;
};/*}}}*/

// filter + model
template<typename Values, template<typename> class Filter, template<typename> class Model>/*{{{*/
class FilterModel : public virtual Filter<Values>, public virtual Model<Values>
{
protected:
    static_assert( is_base_of<AbstractValues<
                        typename Values::Input_t,
                        typename Values::Output_t
                   >, Values>::value );
    static_assert( is_base_of<AbstractFilter<Values>, Filter<Values>>::value );
    static_assert( is_base_of<AbstractModel<Values>,  Model<Values>>::value );

public:
    void print() {
        for(auto v : this->inputs) cout << v << ' ';
        cout << '\n';
        for(auto v : this->outputs) cout << v << ' ';
        cout << '\n';
    }

    FilterModel( Values vals ) : Values( vals ) { }
};/*}}}*/


class LongPoints : public virtual AbstractValues<long, long>/*{{{*/
{
public:
    LongPoints() {  }
    LongPoints( vector<long> inputs, vector<long> outputs ) {
        this->inputs  = inputs;
        this->outputs = outputs;
    }
    LongPoints( LongPoints &other ) {
        this->inputs  = other.inputs;
        this->outputs = other.outputs;
    }
};/*}}}*/

template<typename> // only will take LongPoints{{{
class MyFilter : public virtual AbstractFilter<LongPoints>
{
public:
    void applyFilter()
    {
        vector<long> &inputs  = this->inputs;
        vector<long> &outputs = this->outputs;

        int n = inputs.size();

        map<long, vector<int>> input_to_inds;
        for(int i=0; i<n; ++i)
        {
            input_to_inds[inputs[i]].push_back( i );
        }

        vector<bool> is_outlier( n, false );

        for(auto &[input, inds] : input_to_inds) {
            int m = inds.size();
            if( m <= 1 ) continue;

            long double sum = accumulate(
                inds.begin(), inds.end(), (long double) 0,
                [&](auto aux, auto i) { return aux + outputs[i]; }
            );

            long double sq_sum = accumulate(
                inds.begin(), inds.end(), (long double) 0,
                [&](auto aux, auto i) { return aux + outputs[i] * outputs[i]; }
            );

            auto get_is_outlier = [&]( long double cur_out )
            {
                long double sq_cur_out = cur_out * cur_out;

                long double osum    = sum - cur_out;
                long double omean   = osum / ( m-1 );
                long double osq_sum = sq_sum - sq_cur_out;

                long double sq_diff = ( cur_out - omean ) * ( cur_out - omean );
                long double sq_std  = ( osq_sum - osum * omean * 2)/(m-1) + omean*omean;

                return sq_diff > 9*sq_std;
            };

            for(auto i : inds)
            {
                is_outlier[i] = get_is_outlier( outputs[i] );
            }

            inputs.erase( remove_if(
                inputs.begin(), inputs.end(),
                [&, i=0](auto&) mutable { return is_outlier[i++]; }
            ), inputs.end() );

            outputs.erase( remove_if(
                outputs.begin(), outputs.end(),
                [&, i=0](auto&) mutable { return is_outlier[i++]; }
            ), outputs.end() );
        }
    }
};/*}}}*/

template<typename>/*{{{*/
class MyModel : AbstractModel<LongPoints>
{
public:
    Output_t applyModel( Input_t input )
    {
        vector<Input_t>  &inputs  = this->inputs;
        vector<Output_t> &outputs = this->outputs;

        int n = inputs.size();

        map<Input_t, vector<int>> input_to_inds;
        for(int i=0; i<n; ++i)
        {
            input_to_inds[inputs[i]].push_back( i );
        }

        auto myRound = []( long double out )
        {
            long res = long( out + 0.5 );
            return res;
            return min( (long) 1e6, max( (long) 1e3, res ) );
        };

        if( input_to_inds.size() == 0 )
        {
            return myRound( input * 1000 );
        }

        if( input_to_inds.count( input ) )
        {
            auto &[a, inds] = *input_to_inds.find( input );

            long double mean_out = accumulate(
                inds.begin(), inds.end(), (long double) 0,
                [&](long double aux, int i){ return aux + outputs[i]; }
            ) / inds.size();

            long double ppsq = mean_out / a;
            return myRound( ppsq * input );
        }

        if( input_to_inds.size() == 1 )
        {
            auto &[a, inds] = *input_to_inds.begin();

            long double mean_out = accumulate(
                inds.begin(), inds.end(), (long double) 0,
                [&](long double aux, int i){ return aux + outputs[i]; }
            ) / inds.size();

            long double ppsq = mean_out / a;
            return myRound( ppsq * input );
        }

        return -1;
    }
};/*}}}*/

int main() {
    vector<long> inputs = { 1, 10, 2, 50, 29, 1, 10, 2, 2, 3, 3 };
    vector<long> outputs = { 1, 10, 2, 50, 29, 1, 10, 2, 2, 0, 1000 };
    LongPoints longPoints = LongPoints( inputs, outputs );

    auto myFilterModel = FilterModel<LongPoints, MyFilter, MyModel>( longPoints );

    myFilterModel.print();

    cout << myFilterModel.applyModel( 1 ) << '\n';
    cout << myFilterModel.applyModel( 10 )<< '\n';
    cout << myFilterModel.applyModel( 2 ) << '\n';
    cout << myFilterModel.applyModel( 3 ) << '\n';

    myFilterModel.applyFilter();
    myFilterModel.print();

    cout << myFilterModel.applyModel( 1 ) << '\n';
    cout << myFilterModel.applyModel( 10 )<< '\n';
    cout << myFilterModel.applyModel( 2 ) << '\n';
    cout << myFilterModel.applyModel( 3 ) << '\n';

    return 0;
}
