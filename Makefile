all: pdf

pdf: fz.tex
	astyle *.cpp -r -A1 --indent=spaces=4
	xelatex fz.tex
	xelatex fz.tex

clean:
	rm -f fz.aux fz.log fz.out fz.toc fz.pdf
	rm -f `find . -name *.orig`
