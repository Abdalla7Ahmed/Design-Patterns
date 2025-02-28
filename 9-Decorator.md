
**Decorator** is a structural design pattern that lets you attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors.


## Structure
![screen](./images/9.1.png)


1-The **Component** declares the common interface for both wrappers and wrapped objects.
2-**Concrete Component** is a class of objects being wrapped. It defines the basic behavior, which can be altered by decorators.
3-**Concrete Component** is a class of objects being wrapped. It defines the basic behavior, which can be altered by decorators.
4-**Concrete Decorators** define extra behaviors that can be added to components dynamically. Concrete decorators override methods of the base decorator and execute their behavior either before or after calling the parent method.
5-The **Client** can wrap components in multiple layers of decorators, as long as it works with all objects via the component interface.
