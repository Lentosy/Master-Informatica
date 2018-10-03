@echo off
	for /R "E:\Master Informatica\Gevorderde algoritmen\Samenvatting\img" %%f in (*.dot) do (
	dot img\%%~nf%%~xf -Tpng -o img\%%~nf.png
)
