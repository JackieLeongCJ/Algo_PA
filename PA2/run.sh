ulimit -s 262144

# ./bin/mps --method=bu inputs/12.in outputs/12.out
# ./bin/mps --method=bu inputs/1000.in outputs/1000.out
# ./bin/mps --method=bu inputs/10000.in outputs/10000.out
# ./bin/mps --method=bu inputs/60000.in outputs/60000.out
# ./bin/mps --method=bu inputs/100000.in outputs/100000.out

./bin/mps inputs/12.in outputs/12.out
./bin/mps inputs/1000.in outputs/1000.out
./bin/mps inputs/10000.in outputs/10000.out
./bin/mps inputs/60000.in outputs/60000.out
./bin/mps inputs/100000.in outputs/100000.out

# ./bin/mps --method=bu inputs/22_self.in outputs/22_self.out


# ./bin/mps --method=td test_inputs/12.in outputs/12_td.out
# ./bin/mps --method=td test_inputs/1000.in outputs/1000_td.out
# ./bin/mps --method=td test_inputs/10000.in outputs/10000_td.out
# ./bin/mps --method=td test_inputs/20000.in outputs/20000_td.out
# ./bin/mps --method=td test_inputs/40000.in outputs/40000_td.out
# ./bin/mps --method=td test_inputs/60000.in outputs/60000_td.out
# ./bin/mps --method=td test_inputs/80000.in outputs/80000_td.out
# ./bin/mps --method=td test_inputs/100000.in outputs/100000_td.out
# ./bin/mps --method=td test_inputs/120000.in outputs/120000_td.out
# ./bin/mps --method=td test_inputs/180000.in outputs/180000_td.out

# ./bin/mps --method=td test_inputs/12.in outputs/12_yw.out
# ./bin/mps --method=td test_inputs/1000.in outputs/1000_yw.out
# ./bin/mps --method=td test_inputs/10000.in outputs/10000_yw.out
# ./bin/mps --method=td test_inputs/20000.in outputs/20000_yw.out
# ./bin/mps --method=td test_inputs/40000.in outputs/40000_yw.out
# ./bin/mps --method=td test_inputs/60000.in outputs/60000_yw.out
# ./bin/mps --method=td test_inputs/80000.in outputs/80000_yw.out
# ./bin/mps --method=td test_inputs/100000.in outputs/100000_yw.out
# ./bin/mps --method=td test_inputs/120000.in outputs/120000_yw.out
# ./bin/mps --method=td test_inputs/180000.in outputs/180000_yw.out


# ./bin/mps --method=td inputs/22_self.in outputs/22_self_td.out