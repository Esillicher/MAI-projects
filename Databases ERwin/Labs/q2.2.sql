# Посчитать кол-во заказов, в которых участвует каждый товар (вывести № товара, название, цвет, кол-во заказов)

SELECT Zakazy.n_tovara, COUNT(Zakazy.n_zakaza) AS number_of_orders;
 FROM ;
     p1!zakazy;
 GROUP BY Zakazy.n_tovara;
 INTO CURSOR tmp  
 
 SELECT DISTINCT tmp.n_tovara, Tovary.tname, Tovary.color, tmp.number_of_orders;
 FROM tmp, Tovary;
 WHERE tmp.n_tovara=Tovary.n_tovara