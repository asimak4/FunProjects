//
//  DeliveryView.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/15/20.
//

import Foundation
import SwiftUI
import Firebase

struct DeliveryView: View {
    var homeData: HomeViewModel
    var delivery: Delivery
    
    var body: some View {
        
        VStack{
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
                ForEach(1...5,id: \.self){ index in
                    Image(systemName: "star.fill")
                        //.foregroundColor(index <= Float(truncating: delivery.rating) ? .pink : .gray)
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
                
                Spacer(minLength: 20)
                
                // ----------------------------------------------------------------------------
               /* NavigationLink(destination: ChatView(homeData: homeData, delivery: delivery)) {
                    HStack(spacing: 15){
                        Image(systemName: "message")
                            .font(.title)
                            .foregroundColor(.pink)
                    }
                }
               
                
                // ----------------------------------------------------------------------------
                if(customerSide){
                    NavigationLink(destination: finishedView(delivery: delivery)) {
                        HStack(spacing: 15){
                            Image(systemName: "checkmark")
                                .font(.title)
                                .foregroundColor(.pink)
                        }
                    }
                }else{
                    NavigationLink(destination: DriverHome()) {
                        HStack(spacing: 15){
                            Image(systemName: "checkmark")
                                .font(.title)
                                .foregroundColor(.pink)
                        }
                    }
                }
                 */
                
                // ----------------------------------------------------------------------------
                
                
                
            }
        }
    }
}

struct DeliveryView_Previews: PreviewProvider {
    static var previews: some View {
        /*@START_MENU_TOKEN@*/Text("Hello, World!")/*@END_MENU_TOKEN@*/
    }
}
