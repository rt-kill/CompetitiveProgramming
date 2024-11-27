def BlackBox( I ):
    if len(I) <= 4 : exit("Too small Banana")
    A = []
    cur_index = 0

    while( len(I) >= 2 ):
        cur_val = I[cur_index]
        A.append( I[cur_index] )
        I.pop(cur_index) # remove
        cur_index = ( cur_index + cur_val - 1 ) % len(I)

    A.append(I[0]);

    tmp = A[0]
    A[0] = A[A[len(A)-1]%(len(A)-1)]
    A[A[len(A)-1]%(len(A)-1)] = tmp

    return A
