#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Widget : public std::enable_shared_from_this<Widget> {
public:
    Widget(const std::string& id)
        : id(id), width(0), height(0), x(0), y(0), z(0), parent(nullptr) {}

    void addWidget(std::shared_ptr<Widget> child) {
        children.push_back(child);
        child->z = children.size() - 1;
        child->parent = shared_from_this();
    }

    void removeWidget(std::shared_ptr<Widget> child) {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end()) {
            children.erase(it);
            child->parent = nullptr;
            child->z = 0;
        }
    }

    std::vector<std::shared_ptr<Widget>>& getChildren() {
        return children;
    }

    std::string id;
    int width;
    int height;
    int x;
    int y;
    int z;
    std::shared_ptr<Widget> parent;
    std::vector<std::shared_ptr<Widget>> children;
};

void iterate_children(std::shared_ptr<Widget> widget, int level=0) {
    std::string indent = std::string(level, ' ');
    std::string parent_id = widget->parent ? widget->parent->id : "";
    std::cout << indent << widget->id << ", z=" << widget->z << ", x=" << widget->x << ", y=" << widget->y
        << ", width=" << widget->width << ", height=" << widget->height << ", parent=" << parent_id << "\n";
    for (auto child : widget->children) {
        iterate_children(child, level+1);
    }
}

int main() {
    auto root = std::make_shared<Widget>("root");
    root->width = 100;
    root->height = 100;

    auto child1 = std::make_shared<Widget>("child1");
    child1->width = 50;
    child1->height = 50;
    child1->x = 10;
    child1->y = 10;
    root->addWidget(child1);

    auto child2 = std::make_shared<Widget>("child2");
    child2->width = 75;
    child2->height = 75;
    child2->x = 30;
    child2->y = 30;
    root->addWidget(child2);

    auto child3 = std::make_shared<Widget>("child3");
    child3->width = 40;
    child3->height = 40;
    child3->x = 50;
    child3->y = 50;
    child2->addWidget(child3);


    iterate_children(root);

    root->removeWidget(child2);
    child1->addWidget(child2);
    
    iterate_children(root);
        
    return 0;
  }

