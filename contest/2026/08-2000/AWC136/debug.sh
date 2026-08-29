while true; do
    ./generator > input.txt
    ans1=$(./C < input.txt)
    ans2=$(./C2 < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done