while true; do
    ./generator > input.txt
    ans1=$(./F3 < input.txt)
    ans2=$(./F_TLE < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done