# Optimal resource production system

## MacOS - ![Build](https://github.com/dolovnyak/orp-system/actions/workflows/build.yml/badge.svg?branch=master)


Program that calculate approximately optimal way to produce resources with verifier.
--------------

#### There are two entity with which we work: `resource` and `process`.
#### Process recive required resources and returns the result resources for N cycles.
#### We have source resources at the start and choose what resources we want to optimize.

#### Example:
```
# source resource template:
# resource_name:num

euro:20
apple:5

# process template:   
# proc_name:(req_resource1:num1;req_resource2:num2;[...]):(res_resource1:num1;res_resource2:num2;[...]):cycles_to_work

make_apple_juice(euro:1;apple:5):(euro:10):10
buy_apple(euro:1):(apple:2):5

# resources to optimize template:
# optimize:(resource_name1;resource_name2;[...])

optimize:(euro)
```

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
