select e.name as employee
from Employee e join employee m
on e.managerId=m.id where e.salary>m.salary;