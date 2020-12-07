//
//  PlaceOrder.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/15/20.
//

import Foundation
import SwiftUI

struct PlaceOrder: View {
    @ObservedObject var HomeModel: HomeViewModel
    var delivery: Delivery
    @Binding var displayOrderScreen:Bool
    @State var userOrder: String = ""

    var body: some View {
        ZStack {
                Color.white
                VStack {
                    HStack(spacing: 8){
                        Text("Place Order")
                            .font(.title)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                        
                        Button(action: {
                            displayOrderScreen = false
                        }){
                            Image(systemName: "xmark")
                                .font(.title)
                                .foregroundColor(.pink)
                        }
                        
                    }.padding(.bottom, 20)
                    
                    
                    HStack(spacing: 8){
                        
                        Text(delivery.restaurant)
                            .font(.title2)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                        
                    }
                                
                    HStack{
                        
                        Text(delivery.name)
                            .font(.title3)
                            .foregroundColor(.black)
                            .lineLimit(2)
                        
                        Spacer(minLength: 0)
                        
                        // Ratings View....
                        let actual = Int(Float(truncating: delivery.rating).rounded(.toNearestOrAwayFromZero))
                        ForEach(1...5,id: \.self){index in
                            
                            Image(systemName: "star.fill")
                                .foregroundColor(index <= Int(truncating: NSNumber(value: actual)) ? .pink : .gray)
                        }
                    }
                    
                    Spacer()
                    
                    HStack(){
                        
                        Text("Time left to order: " + delivery.time_window.stringValue + " min")
                            .font(.caption)
                            .foregroundColor(.gray)
                        
                        Spacer(minLength: 0)
                        
                    }
                    
                    HStack(){
                        
                        Text("Driver notes: " + delivery.notes)
                            .font(.caption)
                            .foregroundColor(.gray)
                            .lineLimit(2)
                        
                        Spacer(minLength: 0)
                        
                    }.padding(.bottom, 20)
                    
                    
                    HStack(){
                        
                        Text("Your Order: ")
                            .font(.title3)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        

                        TextField("Enter order...", text: $userOrder)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        Spacer(minLength: 0)
                        
                    }.padding(.bottom, 20)
                    
                    //Spacer()
                    
                    Button(action: {
                        self.displayOrderScreen = false
                        HomeModel.sendOrder(delivery: delivery, order: userOrder)
                    }, label: {
                        Text("Place Order").foregroundColor(.pink)
                    })
                }.padding()
            }
            .frame(minWidth: 300, minHeight: 200 , alignment: .top).fixedSize(horizontal: true, vertical: true)
            .cornerRadius(20).shadow(radius: 20)
      }
}
