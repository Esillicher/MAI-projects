# Определить менеджеров, которые никогда не использовали выбранный товар

SELECT DISTINCT Menedgery.mname, Menedgery.last_name,;
  Menedgery.otchestvo, Menedgery.n_podr, Zakazy.n_m;
 FROM ;
     Menedgery,;
    Zakazy;
 WHERE  Menedgery.n_m = Zakazy.n_m;
   AND  Zakazy.n_m NOT IN (SELECT Zakazy.n_m FROM Zakazy WHERE Zakazy.n_tovara = 25)
