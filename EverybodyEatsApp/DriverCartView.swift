//
//  DriverCartView.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 12/6/20.
//

import Foundation
import SwiftUI
import Firebase

struct DriverCartView: View {
    @ObservedObject var homeData: DriverHomeViewModel
    var body: some View {
        if Auth.auth().currentUser != nil {
        VStack(spacing: 10){
        
            HStack(spacing: 20){
                NavigationLink(destination: DriverHome()){
                    Image(systemName: "chevron.left")
                        .font(.system(size: 26, weight: .heavy))
                        .foregroundColor(Color("pink"))
                }
                
                Text("Accepted Orders")
                    .font(.title)
                    .fontWeight(.heavy)
                    .foregroundColor(.black)
                Spacer()
                
            }
            .padding()
            
            ScrollView(.vertical, showsIndicators: false, content: {
                Divider()
                
                VStack(spacing: 20){
                    ForEach(homeData.acceptedOrders){Order in
                     //   Button(action: {self.displayOrderScreen = true; self.orderPressed=Delivery}) {
                            HStack{
                                VStack{
                                    HStack(spacing: 8){
                                        
                                        Text(Order.restaurant)
                                            .font(.title2)
                                            .fontWeight(.bold)
                                            .foregroundColor(.black)
                                        
                                        Spacer(minLength: 0)
                                        
                                    }.padding(.bottom,2)
                                    
                                    
                                    VStack(){
                                    HStack(){
                                    
                                        Text(Order.order)
                                            .font(.title3)
                                            .foregroundColor(.black)
                                        
                                        Spacer(minLength: 0)
                                    }.padding(.bottom,2)
                                    .padding(.leading, 20)
                                    
                                    }
                                                
                                    HStack{
                                        
                                        Text("Driver: " + Order.name)
                                            .font(.body)
                                            .foregroundColor(.black)
                                            .lineLimit(2)
                                        
                                        Spacer(minLength: 0)
                                                                               
                                    }.padding(.leading, 20)
                                    
                                    Spacer()
                                    
                                    HStack{
                                        Spacer()
                                        NavigationLink(destination: DriverChatView(homeData: homeData, order: Order)) {
                                            HStack(spacing: 15){
                                                Image(systemName: "message")
                                                    .font(.title)
                                                    .foregroundColor(.pink)
                                            }
                                        }
                                        /*
                                        NavigationLink(destination: OrderView()) {
                                            HStack(spacing: 15){
                                                Image(systemName: "map")
                                                    .font(.title)
                                                    .foregroundColor(.pink)
                                            }
                                        }
                                        
                                        NavigationLink(destination: OrderView()) {
                                            HStack(spacing: 15){
                                                Image(systemName: "dollarsign.circle")
                                                    .font(.title)
                                                    .foregroundColor(.pink)
                                            }
                                        }*/
                                        
                                        NavigationLink(destination: finishedView(order: Order)) {
                                            HStack(spacing: 15){
                                                Image(systemName: "checkmark")
                                                    .font(.title)
                                                    .foregroundColor(.pink)
                                            }
                                        }
                                        
                                    }
                                   
                                    
                                    
                                    Spacer()
                                }
                                    .frame(width: UIScreen.main.bounds.width - 30)
                                    //.border(Color.gray)
                            }
                      //  }
                        
                        Divider()
                    }
                }
                .padding(.top,10)
            })
            
            Spacer()
        }.onAppear(perform: {
            // login to database
            homeData.getAcceptedOrders()
        }).navigationBarHidden(true)
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
}

    
