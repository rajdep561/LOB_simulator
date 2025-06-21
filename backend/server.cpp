#include<iostream>
#include <string>
#include <map>
#include <vector>
#include<iomanip>

enum class OrderType {
    BUY,
    SELL
};


struct Order {
    int orderId;
    double price;
    int quantity;
    OrderType type;

    Order(int id,double p,int q,OrderType t)
    : orderId(id),price(p),quantity(q),type(t) {}

    void print() const {
        std::cout<<"order ID"<<orderId
                <<", PRice:" <<std::fixed << std::setprecision(2) << price
                << "Quantity" << quantity
                << "Type" <<(type == OrderType::BUY ? "BUY":"SELL")
                << std::endl;
    }

};


struct Order;

class OrderBook {
    public:
    int nextOrderId =1;
    std::map<double, std::vector<Order>> bids;
    std::map<double,std::vector<Order>> asks;

    void addOrder(double price, int quantity,OrderType type);

    void displayOrderBook() const;

    private:
    void matchOrders(Order& newOrder);
};

void OrderBook::addOrder(double price,int quantity,OrderType type){
 Order newOrder(nextOrderId++,price,quantity,type);
std::cout << "\n processing new order "<<std::endl;
newOrder.print();
matchOrders(newOrder);

if (newOrder.quantity > 0){
    if (newOrder.type == OrderType::BUY){
        bids[newOrder.price].push_back(newOrder);
        std::cout<<"REmainging buy order added to this."<<std::endl;

    }else{
        asks[newOrder.price].push_back(newOrder);
        std::cout << "Remaining SELL order added to this."<<std::endl;

    }

}else {
    std::cout << "Order fully executed"<< std::endl;

}
}

void OrderBook::displayOrderBook() const {
    std::cout << "Current ORder Book"<<std::endl;
    std::cout<< "Asks (Sell ORders)"<<std::endl;
    if (asks.empty()){
        std::cout <<"No ask orders:: "<<std:endl;


    }else{
        for (const auto& pair : asks){
            double price = pair.first;
            const std::vector<Order>& ordersAtPrice = pair.second;
            int totalQuantity = 0;
            for (const auto& order : ordersAtPrice){
                totalQuantity+= order.quantity;
            }
            std::cout<<"Price"<<std::fixed<<std::setprecision(2)<<price;
            << "| quantity:"<<totalQuantity;
            <<"Orders:"<<ordersAtPrice.size()<<std::endl;
        }
    }
 //Bids buy orders
}