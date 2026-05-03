while true; do
    ./generator > input.txt
    ans1=$(./G < input.txt)
    ans2=$(./G_DSU_on_Tree < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done