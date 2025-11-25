g++ J_generator.cpp -o J_generator
g++ J.cpp -o J
g++ J_gutyoku.cpp -o J_gutyoku

while true; do
    ./J_generator > input.txt
    ans1=$(./J < input.txt)
    ans2=$(./J_gutyoku < input.txt)
    if [ "$ans1" != "$ans2" ]; then
        echo "Wrong Answer"
        exit
    fi
done