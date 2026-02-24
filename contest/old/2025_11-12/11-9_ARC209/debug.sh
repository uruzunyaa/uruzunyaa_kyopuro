while true; do
    ./Dgenerator > input.txt
    ans1=$(./D < input.txt)
    ans2=$(./Dgutyoku < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done