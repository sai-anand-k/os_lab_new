echo enter a number
read n
let 'f=1'
let 's=0'

if [[ $n =~ ^[1-9][0-9]* ]]
then 
    while ((n>0))
    do
       let 'r=n%10'
       let 's+=r'
       let 'n=n/10'
    done
    echo sum of digits are $s
else
    echo invalid number 
fi
    