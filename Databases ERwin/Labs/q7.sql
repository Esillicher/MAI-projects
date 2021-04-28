# Контрагенты, которые заказывали товаров большо среднего

SELECT Zakazy.n_kontragenta AS nk, SUM(Zakazy.qty) AS sqty;
 FROM ;
     Zakazy;
 GROUP BY Zakazy.n_kontragenta;
 INTO CURSOR tmp  
  
SELECT tmp.NK, Kontragenty.shop_name FROM tmp, Kontragenty;
 WHERE tmp.SQty > (SELECT AVG(tmp.SQty) FROM tmp) AND Kontragenty.n_k=tmp.NK