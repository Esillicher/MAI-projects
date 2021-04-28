# Определить кол-во заказов у каждого менеджера (вывести № менеджера, № подразделения, ФИО и кол-во заказов)

SELECT Zakazy.n_m, COUNT(Zakazy.n_zakaza) AS number_of_orders;
 FROM ;
     Zakazy;
 GROUP BY Zakazy.n_m;
 INTO CURSOR tmp  
 
 SELECT DISTINCT tmp.n_m, menedgery.n_podr, Menedgery.last_name, Menedgery.mname, tmp.number_of_orders;
 FROM tmp, menedgery, podr;
 WHERE menedgery.n_m=tmp.n_m