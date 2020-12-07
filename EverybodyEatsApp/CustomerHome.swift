//
//  CustomerHome.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/14/20.
//

import Foundation
import SwiftUI
import CoreLocation
import Firebase

struct CustomerHome: View {
    @StateObject var HomeModel = HomeViewModel()
    @StateObject var HomeMode2 = HomeViewModel()
    @State var displayOrderScreen: Bool = false
    @State var orderPressed: Delivery = Delivery()
    
    var body: some View {
        if Auth.auth().currentUser != nil {
            ZStack {
                VStack(spacing: 10){
                    
                    HStack(spacing: 15){
                        
                        Button(action: {
                            withAnimation(.easeIn){HomeModel.showMenu.toggle()}
                        }, label: {
                            Image(systemName: "line.horizontal.3")
                                .font(.title)
                                .foregroundColor(.pink)
                        })
                        Text("Resturants Available")
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding([.horizontal,.top])
                    
                    Divider()
                    
                    Spacer()
                    
                    //Location stuff
                       .onAppear(perform: {
                            HomeModel.locationManager.delegate = HomeMode2
                            HomeModel.locationManager.requestWhenInUseAuthorization()
                        })
                    
                    
                    ZStack{
                        if (displayOrderScreen != false) {
                            PlaceOrder(HomeModel: HomeModel, delivery: orderPressed, displayOrderScreen: $displayOrderScreen)
                            .zIndex(2)
                            .padding(.top, -40)
                        }
                        
                        ScrollView(.vertical, showsIndicators: false, content: {
                            Divider()
                            
                            VStack(spacing: 20){
                                ForEach(HomeModel.deliveries){Delivery in
                                    Button(action: {self.displayOrderScreen = true; self.orderPressed=Delivery}) {
                                        HStack{
                                            DeliveryView(homeData: HomeModel, delivery: Delivery)
                                                .frame(width: UIScreen.main.bounds.width - 30)
                                                //.border(Color.gray)
                                        }
                                    }
                                    
                                    Divider()
                                }
                            }
                            .padding(.top,10)
                            .zIndex(0)
                        })
                    }
                }
                
                // menu
                HStack{
                    
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
                )
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
    
}

struct CustomerHome_Previews: PreviewProvider {
    static var previews: some View {
        CustomerHome()
    }
}
