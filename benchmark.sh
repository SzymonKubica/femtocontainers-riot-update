sum=0
iterations=100
for ((i=0; i<$iterations; i++));
do
  time=$(./execute-bpf.sh wlp3s0 fe80::7a21:84ff:fe9d:10 0)
  echo "Iteration $i: $time [us]"
  sum=$(($sum + $time))
done

echo "Average: $(($sum / $iterations)) [us]"
