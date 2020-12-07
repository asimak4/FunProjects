//
//  OrderFinishedView.swift
//  ErryBody Eats
//
//  Created by Alex Simak on 12/2/20.
//

import Foundation
import SwiftUI
import Firebase



struct finishedView: View {
    @ObservedObject var HomeModel = HomeViewModel()
    @ObservedObject var DriverHomeModel = DriverHomeViewModel()
    var order: Order
    @State var rating = 5
    @State var newTotalRatings = 0
    @State var newRating = 0
    
    //@State var displayOrderScreen: Bool = false
    //@State var orderPressed: Delivery = Delivery()
    var body: some View {
        if Auth.auth().currentUser != nil {
            ZStack {
                VStack(spacing: 10){
                    
                    HStack(spacing: 20){
                        if(customerSide){
                            NavigationLink(destination: CartView(homeData: HomeModel)){
                                Image(systemName: "chevron.left")
                                    .font(.system(size: 26, weight: .heavy))
                                    .foregroundColor(Color("pink"))
                            }
                        } else {
                            NavigationLink(destination: DriverCartView(homeData: DriverHomeModel)){
                                Image(systemName: "chevron.left")
                                    .font(.system(size: 26, weight: .heavy))
                                    .foregroundColor(Color("pink"))
                            }
                        }
                        
                        Text("Order Completed")
                            .font(.title)
                            .fontWeight(.heavy)
                            .foregroundColor(.black)
                        Spacer()
                    }
                    .padding()
                    
                    Divider()
                    VStack{
                        if(customerSide){
                            Text("Please Rate your driver: ").font(.title2)
                        } else {
                            Text("Please Rate your customer: ").font(.title2)
                        }
                        HStack{
                            ForEach(1...5,id: \.self){index in
                                Image(systemName: "star.fill")
                                    .foregroundColor(index <= Int(truncating: NSNumber(value: rating)) ? .pink : .gray)
                            }
                        }
                        Stepper(value: $rating, in:0...5) {
                            Text("\(rating) Stars")
                        }.padding(.horizontal,20)
                    }
                    //Button(action: {
                    NavigationLink(destination: getDestination()){
                        Text("Submit")
                            .font(.title3)
                            .foregroundColor(.pink)
                    }.simultaneousGesture(TapGesture().onEnded{
                        
                        //print(HomeModel.users)
                        let driver = HomeModel.users
                        let avgRating = driver[0].ratingAvg
                        let newTotal = driver[0].ratingsTotal + 1
                        var newAvgRating = (avgRating) * Float(driver[0].ratingsTotal) + Float(rating)
                        newAvgRating = newAvgRating / Float(newTotal)
                        
                        var trialDelivery = HomeModel.deliveries[0].id
                        //var trialOrder = HomeModel.cart[0].deliveryID
                        var i = 0
                        while(i < HomeModel.deliveries.count){
                            if(HomeModel.deliveries[i].driver_id == driver[0].id){
                                trialDelivery = HomeModel.deliveries[i].id
                            }
                            i+=1
                        }
                        
                        /*i = 0
                        while(i < HomeModel.cart.count){
                            if(HomeModel.cart[i].deliveryID == driver[0].id){
                                trialOrder = HomeModel.cart[i].id
                            }
                            i+=1
                        }*/
                        
                        HomeModel.updateDriverRating(uid: order.deliveryID, ratingAvg: newAvgRating, db_docid: trialDelivery)
                        HomeModel.updateUserRating(uid: order.deliveryID, ratingAvg: newAvgRating, ratingsTotal: newTotal, db_docid: driver[0].docid)
                        //HomeModel.updateOrderRating(uid: delivery.driver_id, ratingAvg: newAvgRating, db_docid: trialOrder)
                        
                        if(customerSide){
                            HomeModel.completeOrder(order: order)
                        } else {
                            DriverHomeModel.completeOrder(order: order)
                        }
                        
                    })
                    Spacer()
                    
                    
                }.onAppear(perform: {
                    HomeModel.getUserData(uid: order.deliveryID)
                    HomeModel.fetchData()
                })
                
                // menu
               /* HStack{
                    Menu(homeData: HomeModel)
                        // Move Effect From Left....
                        .offset(x: HomeModel.showMenu ? 0 : -UIScreen.main.bounds.width / 1.6)
                    
                    Spacer(minLength: 0)
                }
                .background(
                    Color.black.opacity(HomeModel.showMenu ? 0.3 : 0).ignoresSafeArea()
                        // clsing when Taps on outside...
                        .onTapGesture(perform: {
                            withAnimation(.easeIn){HomeModel.showMenu.toggle()}
                        })
                )*/
            }.onAppear(perform: {
                // fetch data from database
                HomeModel.fetchData()
            })
            .navigationBarHidden(true)
            .navigationBarBackButtonHidden(true)
        }
        else{
            NavigationView{
                WelcomeView()
                    .navigationBarHidden(true)
                    .navigationBarBackButtonHidden(true)
            }.navigationBarHidden(true)
            .navigationBarBackButtonHidden(true)
            Spacer()
        }
    }
    
    func getDestination() -> AnyView {
        if(customerSide) {
            return AnyView(CustomerHome())
        } else {
            return AnyView(DriverHome())
        }
    }
    
}



struct finishedView_Previews: PreviewProvider {
    static var previews: some View {
        CustomerHome()
    }
}

