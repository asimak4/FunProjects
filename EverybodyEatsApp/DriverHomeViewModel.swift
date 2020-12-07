//
//  DriverHomeViewModel.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 12/1/20.
//

import Foundation
import SwiftUI
import Firebase
import CoreLocation

class DriverHomeViewModel: NSObject, ObservableObject, CLLocationManagerDelegate{
    @Published var showMenu = false
    @Published var orders: [Order] = []
    @Published var acceptedOrders: [Order] = []
    @Published var completedOrders: [Order] = []
    @Published var cart: [Cart] = []
    @Published var messages: [Message] = []
    @Published var locationManager = CLLocationManager()
    @Published var search = ""
    @Published var deliveryExists = false
    
    var uid = Auth.auth().currentUser?.uid
    
    // Fetching Order Data
    
    func fetchData(){
        
        let db = Firestore.firestore()
        
        db.collection("deliveries").whereField("driver_id", isEqualTo: uid ?? "")
            .getDocuments() { (querySnapshot, err) in
                if let err = err {
                    print("Error getting documents: \(err)")
                } else {
                    if(querySnapshot!.documents.count > 0) {
                        self.deliveryExists = true
                        
                        db.collection("orders").whereField("delivery_id", isEqualTo: self.uid!).getDocuments { (snap, err) in
                            
                            guard let orderData = snap else{return}
                            
                            self.orders = orderData.documents.compactMap({ (doc) -> Order? in
                                
                                let db_id = doc.documentID
                                print(db_id)
                                let db_deliveryid = doc.get("delivery_id") as! String
                                let db_customerid = doc.get("customer_id") as! String
                                let db_order = doc.get("order") as! String
                                let db_restaurant = doc.get("restaurant") as! String
                                let db_rating = doc.get("rating") as! NSNumber
                                let db_name = doc.get("name") as! String
                                
                                return Order(id: db_id, deliveryID: db_deliveryid, customerID: db_customerid, order: db_order, name: db_name, rating: db_rating, restaurant: db_restaurant)
                            })
                        }
                    }
                }
            }
        
    }
    
    func addDelivery(name: String, restaurant: String, timeWindow: NSNumber, notes: String, rating: NSNumber){
        
        let db = Firestore.firestore()
        
        var ref: DocumentReference? = nil
        ref = db.collection("deliveries").addDocument(data: [
            
            "driver_id": uid!,
            "name": name,
            "restaurant": restaurant,
            "time_window": timeWindow,
            "notes": notes,
            "rating": rating
        ]) { err in
            if let err = err {
                print("Error adding document: \(err)")
            } else {
                print("Document added with ID: \(ref!.documentID)")
            }
        }
    }
    
    func getOrders(){
        
        let db = Firestore.firestore()
        
        db.collection("orders").getDocuments { (snap, err) in
            
            guard let orderData = snap else{return}
            
            self.cart = orderData.documents.compactMap({ (doc) -> Cart? in
                
                let db_id = doc.documentID
                let db_name = doc.get("name") as! String
                let db_restaurant = doc.get("restaurant") as! String
                let db_rating = doc.get("rating") as! NSNumber
                let db_order = doc.get("order") as! String
                
                return Cart(id: db_id, name: db_name, rating: db_rating, restaurant: db_restaurant, deliveryID: db_id, order: db_order)
                
            })
        }
    }
    
    func locationManagerDidChangeAuthorization(_ manager: CLLocationManager) {
        //check location status
        switch manager.authorizationStatus{
        case .authorizedWhenInUse:
            print("Authorized")
        case .denied:
            print("Denied")
        default:
            print("Unknown")
        }
    }
    
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error){
        print(error.localizedDescription)
    }
    
    func getSentMessages(customerId: String){
        
        let db = Firestore.firestore()
        
        db.collection("messages").whereField("fromId", isEqualTo: uid!).whereField("toId", isEqualTo: customerId).order(by: "timestamp", descending: false).getDocuments { (snap, err) in
            
            guard let messageData = snap else{return}
            
            self.messages.append(contentsOf: messageData.documents.compactMap({ (doc) -> Message? in
                
                let db_id = doc.documentID
                let db_fromId = doc.get("fromId") as! String
                let db_toId = doc.get("toId") as! String
                let db_message = doc.get("message") as! String
                let db_timestamp = doc.get("timestamp") as! Int
                
                return Message(id: db_id, fromId: db_fromId, message: db_message, timestamp: db_timestamp, toId: db_toId)
            }))
            
            self.messages.sort{ $0.timestamp < $1.timestamp }
        }
    }
    
    func getRecvMessages(customerId: String){
        
        let db = Firestore.firestore()
        
        db.collection("messages").whereField("toId", isEqualTo: uid!).whereField("fromId", isEqualTo: customerId).order(by: "timestamp", descending: false).getDocuments { (snap, err) in
            
            guard let messageData = snap else{return}
            
            self.messages.append(contentsOf: messageData.documents.compactMap({ (doc) -> Message? in
                
                let db_id = doc.documentID
                let db_fromId = doc.get("fromId") as! String
                let db_toId = doc.get("toId") as! String
                let db_message = doc.get("message") as! String
                let db_timestamp = doc.get("timestamp") as! Int
                
                return Message(id: db_id, fromId: db_fromId, message: db_message, timestamp: db_timestamp, toId: db_toId)
            }))
            
            self.messages.sort{ $0.timestamp < $1.timestamp }
        }
    }
    
    func sendMessage(toId: String, message: String){
        
        let db = Firestore.firestore()
        db.collection("messages").addDocument(data: ["fromId": uid!, "toId": toId, "message": message, "timestamp": Int(Date().timeIntervalSince1970)])
    }
    
    func acceptOrder(order: Order){
        let db = Firestore.firestore()
        
        db.collection("orders_accepted").addDocument(data: [
            
            "delivery_id": order.deliveryID,
            "customer_id": order.customerID,
            "order": order.order,
            "name": order.name,
            "restaurant": order.restaurant,
            "customer_completed": false,
            "driver_completed": false,
            "rating": order.rating,
        ])
        
        db.collection("orders").document(order.id).delete() { err in
            if let err = err {
                print("Error removing document: \(err)")
            } else {
                print("Document successfully removed!")
            }
        }
    }
    
    func getAcceptedOrders(){
        let db = Firestore.firestore()
        
        db.collection("orders_accepted").whereField("delivery_id", isEqualTo: self.uid!).getDocuments { (snap, err) in
            
            guard let orderData = snap else{return}
            
            self.acceptedOrders = orderData.documents.compactMap({ (doc) -> Order? in
                
                let db_id = doc.documentID
                let db_deliveryid = doc.get("delivery_id") as! String
                let db_customerid = doc.get("customer_id") as! String
                let db_order = doc.get("order") as! String
                let db_restaurant = doc.get("restaurant") as! String
                let db_rating = doc.get("rating") as! NSNumber
                let db_name = doc.get("name") as! String
                
                return Order(id: db_id, deliveryID: db_deliveryid, customerID: db_customerid, order: db_order, name: db_name, rating: db_rating, restaurant: db_restaurant)
            })
        }
    }
    
    func completeOrder(order: Order) {
        
        let db = Firestore.firestore()
        let db_order = db.collection("orders_accepted").document(order.id)
        db_order.updateData([
            "driver_completed": true
        ]) { err in
            if let err = err {
                print("Error updating document: \(err)")
            } else {
                print("Document successfully updated")
            }
        }
        
        db_order.getDocument { (document, error) in
            if let document = document, document.exists {
                let customer_completed = document.get("customer_completed") as! Bool
                if(customer_completed == true){
                    db.collection("orders_completed").addDocument(data: [
                        
                        "delivery_id": order.deliveryID,
                        "customer_id": order.customerID,
                        "order": order.order,
                        "name": order.name,
                        "restaurant": order.restaurant,
                    ])
                    
                    db_order.delete() { err in
                        if let err = err {
                            print("Error removing document: \(err)")
                        } else {
                            print("Document successfully removed!")
                        }
                    }
                }
            } else {
                print("Document does not exist")
            }
        }
    }
    
    func getCompletedOrders(){
        let db = Firestore.firestore()
        
        db.collection("orders_completed").whereField("delivery_id", isEqualTo: self.uid!).getDocuments { (snap, err) in
            
            guard let orderData = snap else{return}
            
            self.completedOrders = orderData.documents.compactMap({ (doc) -> Order? in
                
                let db_id = doc.documentID
                let db_deliveryid = doc.get("delivery_id") as! String
                let db_customerid = doc.get("customer_id") as! String
                let db_order = doc.get("order") as! String
                let db_restaurant = doc.get("restaurant") as! String
                let db_name = doc.get("name") as! String
                
                return Order(id: db_id, deliveryID: db_deliveryid, customerID: db_customerid, order: db_order, name: db_name, restaurant: db_restaurant)
            })
        }
    }
    
    func getUserName(userID: String) -> String {
        let db = Firestore.firestore()
        var userName = ""
        
        db.collection("users").whereField("id", isEqualTo: userID)
            .getDocuments() { (querySnapshot, err) in
                if let err = err {
                    print("Error getting documents: \(err)")
                } else {
                    for document in querySnapshot!.documents {
                        let firstName = document.get("first_name") as! String
                        let lastName = document.get("last_name") as! String
                        userName = firstName + " " + lastName
                        print(userName)
                    }
                }
        }
        
        print(userName)
        return userName
    }
    
}


