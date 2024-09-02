# FITS Manipulation

I wondered when I have plate-solved, and found the centre of the image if I could store this data somewhere in the FITS file.

It appears we can.... So 

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

# Build

There are two ways to build the code - if you are not using QT, then just use the makefile.

If you are using QT - then open in QT Creator and build that way.

# Running

This is a command line tool and it expects 3 arguments

  - FILENAME: The Fits file to Modify 
  - RA: Right Asc as a Decimal **Degree**. i.e. 23.321
  - DEC: Declenation as a Decimal **Degreee** i.e. -10.123

```bash
 ./set_centre /Astro/Image/M31/i1.fit 10.2 -23.333 
```




