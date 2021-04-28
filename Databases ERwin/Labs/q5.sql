# Определить пары менеджеров одного подразделения

SELECT Fg.last_name AS ln1, Fg.mname AS mn1, Fb.mname AS mn2,;
  Fb.last_name AS ln2, Fg.n_podr;
 FROM ;
     p1!Menedgery Fg,;
    p1!Menedgery Fb;
 WHERE (  Fg.n_podr = Fb.n_podr;
   AND  Fg.last_name > Fb.last_name );
   AND  Fg.mname > Fb.mname
   
