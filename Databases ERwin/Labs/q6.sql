# Определить менеджеров, которые работали с теми же контрагентами, что и менеджер Кунгурцева

SELECT Menedgery.last_name, Zakazy.n_m, Zakazy.n_kontragenta;
 FROM ;
     Menedgery,;
    Zakazy;
 WHERE  Zakazy.n_m = Menedgery.n_m;
   AND  Menedgery.last_name = ( "Кунгурцева" );
 INTO CURSOR tmp  
   
SELECT DISTINCT Menedgery.last_name, Menedgery.mname, Kontragenty.shop_name, Kontragenty.n_k;
FROM Menedgery, Kontragenty, Zakazy;
WHERE Zakazy.n_kontragenta = tmp.n_kontragenta;
AND Menedgery.n_m = Zakazy.n_m;
   AND  Kontragenty.n_k = Zakazy.n_kontragenta;
AND Zakazy.n_m NOT IN (tmp.n_m)