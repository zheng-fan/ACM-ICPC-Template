all: pdf

pdf: fz.tex
	astyle */*.cpp -A2 --indent=spaces=4
	xelatex fz.tex
	xelatex fz.tex

clean:
	rm -f *.toc *.pdf
