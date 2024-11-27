n,m= list(map(int,input().split()))
nums=list(map(int,input().split()))
nums.sort()
ans=1
l=0
r=n-1
while l<r:
    if nums[r]+nums[l]<=m:
        r-=1
        l+=1
    else:
        r-=1
        ans+=1
print(ans+sum(nums))
