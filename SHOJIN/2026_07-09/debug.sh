while true; do
    ./generator > input.txt
    ans1=$(./ABC205E < input.txt)
    ans2=$(./ABC205E_AC < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done