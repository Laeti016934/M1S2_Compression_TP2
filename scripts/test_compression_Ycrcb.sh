if [ -d "out/$1" ]; then rm -Rf out/$1; fi
mkdir out/$1;
mkdir out/$1/YCrCb;
g++ src/PSNR.cpp -o PSNR -Wall;
g++ src/compressionY.cpp -o compressionY -Wall;
g++ src/decompressionY.cpp -o decompressionY -Wall;
./compressionY img/${1}.ppm out/$1/YCrCb/${1}Y.pgm out/$1/YCrCb/${1}Cr.pgm out/$1/YCrCb/${1}Cb.pgm;
./decompressionY out/$1/YCrCb/${1}Y.pgm out/$1/YCrCb/${1}Cr.pgm out/$1/YCrCb/${1}Cb.pgm out/$1/YCrCb/${1}final.ppm;
./PSNR img/${1}.ppm out/$1/YCrCb/${1}final.ppm;
exit 0;