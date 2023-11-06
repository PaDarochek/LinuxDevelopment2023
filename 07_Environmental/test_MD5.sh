echo 'MD5 "abcde' | ./rhasher >test_MD5.log
if [[ $(grep '#define USE_READLINE' config.h) ]]; then sed -i '1d' test_MD5.log; fi
echo -n 'abcde' | md5sum - >test_MD5.ideal
sed 's/  -$//' -i test_MD5.ideal
cmp test_MD5.log test_MD5.ideal