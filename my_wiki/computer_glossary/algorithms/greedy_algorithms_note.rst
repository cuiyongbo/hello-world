*****************
Greedy algorithms
*****************

**Problem definition:** Suppose we have a set :math:`S={a_1,a_2, \ldots,a_n}` of n proposed activities that wish to use a resource, such as a lecture hall, which can serve only one activity at a time. 
Each activity :math:`a_i` has a start time :math:`s_i` and a finish time :math:`f_i` ,
where :math:`0 \le  s_i \lt f_i \lt \infty`. If selected, activity :math:`a_i` takes place 
during the half-open time interval :math:`[s_i, f_i)`. Activities :math:`a_i` and :math:`a_j`
are compatible if the intervals :math:`[s_i, f_i)` and :math:`[s_j, f_j)` do not overlap. 
That is, :math:`a_i` and :math:`a_j` are compatible if :math:`s_i \ge  f_j` or :math:`s_j \ge  f_i`. 
In the **activity-selection problem**, we wish to select a maximum-size subset of mutually compatible activities.