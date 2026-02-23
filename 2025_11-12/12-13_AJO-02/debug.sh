while true; do
    ./generator > input.txt
    ans1=$(./A < input.txt)
    ans2=$(./A_random < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done