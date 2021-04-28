# Определить подразделение, связанное с максимальным кол-вом контрагентов

SELECT Zakazy.n_m AS nm,;
  COUNT(DISTINCT Zakazy.n_kontragenta) AS cntk;
 FROM ;
     Zakazy;
 GROUP BY Zakazy.n_m;
 INTO CURSOR tmp1  
 
SELECT tmp1.cntk, tmp1.nm AS nm2; 
	FROM tmp1 WHERE tmp1.cntk=(SELECT MAX(tmp1.cntk) AS cntk2 FROM tmp1) INTO CURSOR tmp2
	
SELECT Menedgery.n_podr ;
FROM Menedgery, tmp2;
 WHERE tmp2.nm2=Menedgery.n_m 