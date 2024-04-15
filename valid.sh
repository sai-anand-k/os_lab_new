echo enter a string
read string

if [[ $string =~ ^[a-zA-Z]+[a-zA-Z0-9]*]]
then 
    echo valid string
else
    echo invalid
fi