//
//  AddResturant.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 12/2/20.
//


import Foundation
import SwiftUI

struct AddResturant: View {
    @ObservedObject var HomeModel: DriverHomeViewModel
    @Binding var displayAddResturantScreen:Bool
    @State var userName: String = ""
    @State var notes: String = ""
    @State var rating: NSNumber = 4
    @State var restuarant: String = ""
    @State var timeWindow: String = ""

    var body: some View {
        ZStack {
                Color.white
                VStack {
                    HStack(spacing: 8){
                        Text("Add Restuarant")
                            .font(.title)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                        
                        Button(action: {
                            displayAddResturantScreen = false
                        }){
                            Image(systemName: "xmark")
                                .font(.title)
                                .foregroundColor(.pink)
                        }
                        
                    }.padding(.bottom, 20)
                    
                    HStack(){
                        
                        Text("Your name: ")
                            .font(.title3)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        

                        TextField("Enter name...", text: $userName)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        Spacer(minLength: 0)
                        
                    }.padding(.bottom, 20)
                    
                    
                    HStack(){
                        
                        Text("Restuarant name: ")
                            .font(.title3)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        

                        TextField("Enter restuarant...", text: $restuarant)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        Spacer(minLength: 0)
                        
                    }.padding(.bottom, 20)
                    
                    HStack(){
                        
                        Text("Time window (min): ")
                            .font(.title3)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        

                        TextField("Enter time...", text: $timeWindow)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        Spacer(minLength: 0)
                        
                    }.padding(.bottom, 20)
                    
                    HStack(){
                        
                        Text("Notes: ")
                            .font(.title3)
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        

                        TextField("Enter notes...", text: $notes)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                        Spacer(minLength: 0)
                        
                    }.padding(.bottom, 20)
                    
                    //Spacer()
                    
                    Button(action: {
                        self.displayAddResturantScreen = false
                        let myInteger = Int(timeWindow)
                        let myNumber = NSNumber(value:myInteger!)
                        HomeModel.addDelivery(name: userName, restaurant: restuarant, timeWindow: myNumber, notes: notes, rating: rating)
                        HomeModel.fetchData()
                    }, label: {
                        Text("Add Restuarant").foregroundColor(.pink)
                    })
                }.padding()
            }
            .frame(minWidth: 300, minHeight: 200 , alignment: .top).fixedSize(horizontal: true, vertical: true)
            .cornerRadius(20).shadow(radius: 20)
      }
}

