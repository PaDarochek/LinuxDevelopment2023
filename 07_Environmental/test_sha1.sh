echo 'sha1 "abcde' | ./rhasher >test_sha1.log
if [[ $(grep '#define USE_READLINE' config.h) ]]; then sed -i '1d' test_sha1.log; fi
echo 'A95sVwv+JL/DKMzXyka3bq2vQzQ=' >test_sha1.ideal
cmp test_sha1.log test_sha1.ideal