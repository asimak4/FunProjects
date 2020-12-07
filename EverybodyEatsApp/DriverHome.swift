//
//  DriverHome.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/24/20.
//

import Foundation
import SwiftUI

struct DriverHome: View {
    @StateObject var HomeModel = DriverHomeViewModel()
    @StateObject var HomeModel2 = HomeViewModel()
    @State var displayAddResturantScreen: Bool = false
    //@State var orderPressed: Delivery = Delivery()
    
    var body: some View {
        
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
                    Text("Orders Received")
                        .foregroundColor(.black)
                    
                    Spacer(minLength: 0)
                }
                .padding([.horizontal,.top])
                
                Divider()
                
                Spacer()
                
                //Location stuff
                   .onAppear(perform: {
                        HomeModel.locationManager.delegate = HomeModel2
                        HomeModel.locationManager.requestWhenInUseAuthorization()
                    })
                
                
                if(HomeModel.deliveryExists){
                    ZStack{
                        ScrollView(.vertical, showsIndicators: false, content: {
                            Divider()
                            
                            VStack(spacing: 20){
                                ForEach(HomeModel.orders){Order in
                                    Button(action: {}) {
                                        OrdersAvailableView(homeData: HomeModel, order: Order)
                                            .frame(width: UIScreen.main.bounds.width - 30)
                                    }
                                    
                                    Divider()
                                }
                            }
                            .padding(.top,10)
                            .zIndex(0)
                        })
                    }
                } else {
                    ZStack{
                        if (displayAddResturantScreen != false) {
                            AddResturant(HomeModel: HomeModel, displayAddResturantScreen: $displayAddResturantScreen)
                            .zIndex(2)
                            .padding(.top, -40)
                        }
                        
                        VStack{
                            Text("What restuarant are you going to?")
                                .font(.title)
                                .padding()
                                .multilineTextAlignment(.center)
                            
                            Button(action: {
                                    self.displayAddResturantScreen = true}) {
                                HStack {
                                    Text("Add Restuarant")
                                        //.fontWeight(.semibold)
                                        .font(.title2)
                                        .multilineTextAlignment(.center)
                                }
                                .padding()
                                .foregroundColor(.white)
                                .background(Color.pink)
                                .cornerRadius(40)
                            }
                        }
                        .zIndex(0)
                    }
                    Spacer()
                }
            }
            
            // menu
            HStack{
                DriverMenu(homeData: HomeModel)
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
                
                //Location stuff
               /*    .onAppear(perform: {
                        HomeModel.locationManager.delegate = HomeMode2
                        HomeModel.locationManager.requestWhenInUseAuthorization()
                    })*/
}
