**Composite** is a structural design pattern that lets you compose objects into tree structures and then work with these structures as if they were individual objects.


## Problem

Using the Composite pattern makes sense only when the core model of your app can be represented as a tree.

For example, imagine that you have two types of objects: `Products` and `Boxes`. A `Box` can contain several `Products` as well as a number of smaller `Boxes`. These little `Boxes` can also hold some `Products` or even smaller `Boxes`, and so on.

Say you decide to create an ordering system that uses these classes. Orders could contain simple products without any wrapping, as well as boxes stuffed with products...and other boxes. How would you determine the total price of such an order?
![screen](./images/8.1.png)


## Solution

The Composite pattern suggests that you work with `Products` and `Boxes` through a common interface which declares a method for calculating the total price.

How would this method work? For a product, it’d simply return the product’s price. For a box, it’d go over each item the box contains, ask its price and then return a total for this box. If one of these items were a smaller box, that box would also start going over its contents and so on, until the prices of all inner components were calculated. A box could even add some extra cost to the final price, such as packaging cost.


## Structure

![screen](./images/8.2.png)

1-The **Component** interface describes operations that are common to both simple and complex elements of the tree.
2-- The **Leaf** is a basic element of a tree that doesn’t have sub-elements.
Usually, leaf components end up doing most of the real work, since they don’t have anyone to delegate the work to.
3-- The **Container** (aka _composite_) is an element that has sub-elements: leaves or other containers. A container doesn’t know the concrete classes of its children. It works with all sub-elements only via the component interface.
Upon receiving a request, a container delegates the work to its sub-elements, processes intermediate results and then returns the final result to the client.
4-The **Client** works with all elements through the component interface. As a result, the client can work in the same way with both simple or complex elements of the tree.



- **Component**: An interface that defines common operations for both leaf and composite objects.
- **Leaf**: Represents individual objects in the hierarchy that do not have any children.
- **Composite**: Represents a node that can have children. It stores child components and implements the component interface to work uniformly with both leaves and composites.

