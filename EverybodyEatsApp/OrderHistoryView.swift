//
//  OrderHistoryView.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 12/7/20.
//

import Foundation
import SwiftUI
import Firebase

struct OrderHistoryView: View {
    @ObservedObject var homeData: HomeViewModel
    var body: some View {
        if Auth.auth().currentUser != nil {
        VStack(spacing: 10){
        
            HStack(spacing: 20){
                NavigationLink(destination: CustomerHome()){
                    Image(systemName: "chevron.left")
                        .font(.system(size: 26, weight: .heavy))
                        .foregroundColor(Color("pink"))
                }
                
                Text("Completed Orders")
                    .font(.title)
                    .fontWeight(.heavy)
                    .foregroundColor(.black)
                Spacer()
                
            }
            .padding()
            
            ScrollView(.vertical, showsIndicators: false, content: {
                Divider()
                
                VStack(spacing: 20){
                    ForEach(homeData.completedOrders){Order in
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
            homeData.getCompletedOrders()
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
