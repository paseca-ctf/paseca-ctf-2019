while :
do
for var in  $(python solve.py | grep paseca)
do
echo "$var";
done 
done
