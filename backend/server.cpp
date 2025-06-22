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
            std::cout<<"Price"<<std::fixed<<std::setprecision(2)<<price
            << "| quantity:"<<totalQuantity
            <<"Orders:"<<ordersAtPrice.size()<<std::endl;
        }
    }
 //Bids buy orders
 std::cout<<"Bids by orders"<<std::endl;
 if (bids.empty()){
    std::cout << "No bid orders"<<std::endl;
 } else {
    for (auto it = bids.rbegin(); it != bids.rend();++it){
        double price = it->first;
        const std::vector<Order>& ordersAtPrice = it->second;
        int totalQuantity = 0;
        for (const auto& order : ordersAtPrice){
            totalQuantity += order.quantity
        }
        std::cout<<"Price:"<<std::fixed<<std::setprecision(2)<<price
        << "| Quantity:"<<totalQuantity
        << "(orders):"<<ordersAtPrice.size()<<std::endl;
    }
 }
 std::cout <<"--------"<<std::endl;
}

private:
    void matchOrders(Order&  newOrder){
        if (newOrder.type == OrderType::BUY){
            auto it = asks.begin()
            while (it !=asks.end() && newOrder.quantity>0){
                double askPrice = it->first;
                if (newOrder.price >= askPrice){
                    std::vector<Order>& ordersAtPrice = it->second;
                    auto orderIt = ordersAtPrice.begin();
                    while (orderIt!= ordersAtPrice.end() && newOrder.quantity>0){
                        Order& existsingOrder = *orderIt;
                        int fillQuantity = std::min(newOrder.quantity,existingOrder.quantity);
                        std::cout << " Matching"<<fillQuantity<< "units:"<<std::endl;
                        std::cout << "New Order:"; newOrder.print();
                        std::cout<< "Existing Ask:";existingOrder.print();
                        newOrder.quantity -= fillQuantity;
                        existingOrder.quantity -= fillQuantity;
                        
                        if (existingOrder.quantity==0){
                            std::cout<<"Existing ask order"<<existingOrder.orderId<<"Fully filled"<<std::endl;
                            orderIt = ordersAtPrice.erase(orderIt);

                        } else {
                            std::cout<< "existing ask order"<<existingOrder.orderId<< "fully filled." << std::endl;
                            ++orderIt;

                        }

                        if (ordersatPrice.empty()){
                            std::cout<<" Ask price level"<<std::fixed <<std::setprecision(2)<<askPrice<<" is now empty. Removing"<<std::endl;
                            it = asks.erase(it);
                        } else {
                            ++it;
                        }

                    } else {
                        break;
                    }
                } else {
                    auto it = bids.rbegin();
                    while (it !=bids.rend() && newOrder.quantity>0){
                        double bidPrice = it->first;
                        if (newOrder.price <=bidprice){}
                    }
                }
            }
        }
    }