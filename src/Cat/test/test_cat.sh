echo test 1 done
for var in main.c test_1_cat.txt test_2_cat.txt test_3_cat.txt test_4_cat.txt test_5_cat.txt test_case_cat.txt
do 

./cat -senbt $var > 1.txt
cat -senbt $var> 2.txt

diff 1.txt 2.txt
done

echo test 2  done
for var2 in -s -n -e --number --squeeze-blank -t -b -tb -sne
do 

./cat $var2 test_case_cat.txt > 1.txt
cat  $var2 test_case_cat.txt > 2.txt

diff 1.txt 2.txt
done
