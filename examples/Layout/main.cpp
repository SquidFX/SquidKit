

// g++ main.cpp -Ithirdparty/install/include -Lthirdparty/install/lib64 -lyogacore -o main

#include <iostream>
#include <yoga/Yoga.h>



void printChildNodes(YGNodeRef parent)
{
    uint32_t numChildren = YGNodeGetChildCount(parent);
    for (uint32_t i = 0; i < numChildren; i++)
    {
        YGNodeRef childNode = YGNodeGetChild(parent, i);
        // Get the layout information of the child node
        float x = YGNodeLayoutGetLeft(childNode);
        float y = YGNodeLayoutGetTop(childNode);
        float width = YGNodeLayoutGetWidth(childNode);
        float height = YGNodeLayoutGetHeight(childNode);

        // Print the index and layout information of the child node
        printf("Child node %d: x=%.2f, y=%.2f, width=%.2f, height=%.2f\n", i, x, y, width, height);

        // Recursively print the child nodes of the current child node
        printChildNodes(childNode);
    }
}



int main() {
  // Create the root node for the horizontal layout
  YGNodeRef rootNode = YGNodeNew();
YGNodeStyleSetFlexDirection(rootNode, YGFlexDirectionColumn);


  // Create the first child node
  YGNodeRef firstChildNode = YGNodeNew();
  YGNodeStyleSetHeightPercent(firstChildNode, 15); // Set height to auto
  YGNodeStyleSetMargin(firstChildNode, YGEdgeBottom, 10);
  YGNodeStyleSetMargin(firstChildNode, YGEdgeRight, 10);
  YGNodeStyleSetFlexGrow(firstChildNode, 1); // Set flexGrow to 1
  YGNodeStyleSetWidth(firstChildNode, YGUndefined); // Set width to auto
  YGNodeInsertChild(rootNode, firstChildNode, 0);

  // Create the second child node
  YGNodeRef secondChildNode = YGNodeNew();
  YGNodeStyleSetHeightPercent(secondChildNode, 70); // Set height to auto
  YGNodeStyleSetMargin(secondChildNode, YGEdgeRight, 10);
  YGNodeStyleSetFlexGrow(secondChildNode, 1); // Set flexGrow to 1
  YGNodeStyleSetWidth(secondChildNode, YGUndefined); // Set width to auto
  YGNodeInsertChild(rootNode, secondChildNode, 1);

  // Create the third child node
  YGNodeRef thirdChildNode = YGNodeNew();
  YGNodeStyleSetHeightPercent(thirdChildNode, 15); // Set height to auto
  YGNodeStyleSetFlexGrow(thirdChildNode, 1); // Set flexGrow to 1
  YGNodeStyleSetWidth(thirdChildNode, YGUndefined); // Set width to auto
  YGNodeInsertChild(rootNode, thirdChildNode, 2);



  // Create the third child node
  YGNodeRef fourthChildNode = YGNodeNew();
  YGNodeStyleSetHeightPercent(fourthChildNode, 15); // Set height to auto
  YGNodeStyleSetFlexGrow(fourthChildNode, 1); // Set flexGrow to 1
  YGNodeStyleSetWidth(fourthChildNode, YGUndefined); // Set width to auto
  YGNodeInsertChild(thirdChildNode, fourthChildNode, 0);




 // Create the third child node
  YGNodeRef fifthChildNode = YGNodeNew();
  YGNodeStyleSetHeightPercent(fifthChildNode, 15); // Set height to auto
  YGNodeStyleSetFlexGrow(fifthChildNode, 1); // Set flexGrow to 1
  YGNodeStyleSetWidth(fifthChildNode, YGUndefined); // Set width to auto
  YGNodeInsertChild(fourthChildNode, fifthChildNode, 0);




  // Calculate the layout
  YGNodeCalculateLayout(rootNode, 800, 600, YGDirectionLTR);

  // Set each child's height to be divided by the number of children and the root height
  float childHeight = YGNodeStyleGetHeight(rootNode).value / YGNodeGetChildCount(rootNode);
  YGNodeStyleSetHeight(firstChildNode, childHeight);
  YGNodeStyleSetHeight(secondChildNode, childHeight);
  YGNodeStyleSetHeight(thirdChildNode, childHeight);

 // Get the number of children of the root node
printChildNodes(rootNode);



  // Free the nodes and their children
  YGNodeFreeRecursive(rootNode);

  return 0;
}

