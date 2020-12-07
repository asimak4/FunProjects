//
//  DriverMenu.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 12/6/20.
//


import Foundation
import SwiftUI
import Firebase

struct DriverMenu: View {
    @ObservedObject var homeData : DriverHomeViewModel
    @State var viewState = CGSize.zero
    @State var MainviewState =  CGSize.zero
    var body: some View {
            VStack{
                NavigationLink(destination: DriverHome()) {
                
                    HStack(spacing: 15){
                        
                        Image(systemName: "house")
                            .font(.title)
                            .foregroundColor(.pink)
                        
                        Text("Home")
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding()
                }
                
                NavigationLink(destination: DriverCartView(homeData: homeData)) {
                    
                    HStack(spacing: 15){
                        
                        Image(systemName: "cart")
                            .font(.title)
                            .foregroundColor(.pink)
                            
                        Text("Orders")
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding()
                }
                
                NavigationLink(destination: DriverOrderHistoryView(homeData: homeData)) {
                    
                    HStack(spacing: 15){
                        
                        Image(systemName: "archivebox")
                            .font(.title)
                            .foregroundColor(.pink)
                        
                        Text("Order History")
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding()
                }
                
                Spacer()

                NavigationLink(destination: CustomerHome()) {
                        
                    HStack(spacing: 15){
                            
                        Image(systemName: "cart.fill")
                            .font(.title)
                            .foregroundColor(.pink)
                        
                        Text("Switch to Customer")
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding()
                }.simultaneousGesture(TapGesture().onEnded{
                    customerSide = true
                })
                
                //var con = ContentView()
                
                NavigationLink(destination: DriverHelpView()) {
                    
                    HStack(spacing: 15){
                        
                        Image(systemName: "questionmark")
                            .font(.title)
                            .foregroundColor(.pink)
                        
                        Text("Help")
                            .fontWeight(.bold)
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding()
                }
                
                                                            
                NavigationLink(destination: WelcomeView()
                                .navigationBarHidden(true)
                                .navigationBarBackButtonHidden(true)) {
                    HStack(spacing: 15){
                            Image(systemName: "arrow.down.backward.circle")
                                .font(.title)
                                .foregroundColor(.pink)
                            Text("Log Out")
                                .fontWeight(.bold)
                                .foregroundColor(.black)
                            Spacer(minLength: 0)
                        }
                    .padding()
                }
                .simultaneousGesture(TapGesture().onEnded{
                    let firebaseAuth = Auth.auth()
                    do {
                       try firebaseAuth.signOut()
                    } catch let signOutError as NSError {
                      print ("Error signing out: %@", signOutError)
                    }
                })
            }
            .padding([.top,.trailing])
            .frame(width: UIScreen.main.bounds.width / 1.6)
            .background(Color.white.ignoresSafeArea())
    }
}
