outdir = html
index = $(outdir)/index.html
source = ../*

all : $(index)

$(index) : $(source)
	doxygen

.PHONY : clean
clean :
	@rm -r $(outdir)/ 
