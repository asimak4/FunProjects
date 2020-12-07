//
//  DriverHelpView.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 12/7/20.
//

import Foundation
import SwiftUI
import Firebase



struct DriverHelpView: View {
    @StateObject var HomeModel = DriverHomeViewModel()
    //@StateObject var HomeMode2 = HomeViewModel()
    //@State var displayOrderScreen: Bool = false
    //@State var orderPressed: Delivery = Delivery()
    
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
                        Text("Frequently Asked Questions")
                            .foregroundColor(.black)
                        
                        Spacer(minLength: 0)
                    }
                    .padding([.horizontal,.top])
                    
                    Divider()
                    Group{
                        Text("Q: Where will I meet the driver?").fontWeight(.bold)
                        Text("A: UMBC Commons")
                        //Text("")
                        Text("Q: How do I know if the Driver is Reliable?").fontWeight(.bold)
                        Text("A: We have constructed a 5 star rating system so depending on the rating, customers can choose their drivers.")
                        Text("Q: Is a Tip and 1$ extra required?").fontWeight(.bold)
                        Text("A: 1$ Extra to the driver is required, a tip is depending on the service or on the users human decency")
                    }
                    Spacer()
                    Text("Any Questions: (443) 668 0050")
                    Text("Special Thanks to Foodversity and Erry'body Eats Associates: Alex Simak, Ashar Nadeem, Adith Maheshwari, Daniyal Khan, Maggie Wang, Naga Panchumarty, Cody Bisram and Musad Haque ").italic().font(.system(size: 10.0))
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

struct DriverHelpView_Previews: PreviewProvider {
    static var previews: some View {
        DriverHelpView()
    }
}

