# Optimal resource production system

## MacOS - ![Build](https://github.com/dolovnyak/orp-system/actions/workflows/build.yml/badge.svg?branch=master)


Program that calculate approximately optimal way to produce resources with verifier.
--------------

#### There are two entity with which we work: `resource` and `process`.
#### Process recive required resources and returns the result resources for N cycles.
#### We have source resources at the start and choose what resources we want to optimize.

Build and run on `MacOS`:
-------
```
cmake -S . -B build
make -C build

./krpsim examples/examaple1.txt 5 (will run 5 seconds)
or 
./krpsim examaples/example1.txt -c 5000 (will run 5000 cycles)


Run verifier example:
./krpsim examaples/examaple1.txt -c 50 >> output.txt
python3 krpsim_verif.py examples/example1.txt output.txt
```

#### Example:
```
# source resource template:
# resource_name:num

euro:20
apple:5

# process template:
# proc_name:(req_resource1:num1;req_resource2:num2;[...]):(res_resource1:num1;res_resource2:num2;[...]):cycles_to_work

make_juice:(euro:1;apple:5):(juice:1):10
sell_juice:(juice:1):(euro:3):5
buy_apple:(euro:1):(apple:10):5

# resources to optimize template:
# optimize:(resource_name1;resource_name2;[...])

optimize:(euro)

Output for this file for 50 cycles (./krpsim this_file_path -c 50):

Nice file! 3 processes, 3 stocks, 1 to optimize
Evaluating .................. done.
Main walk
0:make_juice
1:buy_apple
10:sell_juice
11:make_juice
21:sell_juice
22:make_juice
23:buy_apple
32:sell_juice
33:make_juice
43:sell_juice
No more process doable at time 48
Stock :
 euro => 26
 apple => 5
 juice => 0
```
