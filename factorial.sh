echo "Enter a number:"
read n

fact() 
{
  if (($1 <= 1))
  then
    echo 1
  else 
    echo $(($1 * $(fact $(($1 - 1)))))
  fi
}

if [[ $n =~ ^[0-9]+ ]]
  then
  result=$(fact $n)
  echo "Factorial is $result"
else
  echo "Please enter a valid number."
fi