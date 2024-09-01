# FITS Manipulation

We need a library ... this is available from [https://heasarc.gsfc.nasa.gov/fitsio/](https://heasarc.gsfc.nasa.gov/fitsio/)

However I will use the GitHub version [https://github.com/HEASARC/cfitsio.git](https://github.com/HEASARC/cfitsio.git).

So to build this 

    git clone https://github.com/HEASARC/cfitsio.git 
    cd cfitsio 
    ./configure --prefix=/usr/local/
    make -j4
    make install 

Nice job NASA !! - very simple and quick. 
**Note** I chose to use a */usr/local/* location to save the header (/usr/local/include/) and static library (/usr/local/lib/). If you do not have access to write to these locations choose (or leave out --prefix and the files will be installed locally to your development directory.)

# Read a Fits File 





# Sample file 

I am sure you have a few sample fits files lying around - if not go find some !!



