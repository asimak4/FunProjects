//
//  ContentView.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/14/20.
//

import SwiftUI

/*class checking: ObservedObject {
    @Published var customerSide = false
}*/
public var customerSide = false

struct ContentView: View {
    @State var customerSelected = false
    @State var driverSelected = false
    
    
    var body: some View {
        /*NavigationView{
            CustomerHome()
                .navigationBarHidden(true)
                .navigationBarBackButtonHidden(true)
        }*/
        VStack{
            Text("What would you like to do today?")
                .font(.title)
                .padding()
            HStack {
                NavigationLink(destination: CustomerHome(), isActive: $customerSelected){
                    Button(action: {
                        self.customerSelected = true
                        customerSide = true
                    }) {
                        HStack {
                            Text("Customer")
                                //.fontWeight(.semibold)
                                .font(.title2)
                        }
                        .padding()
                        .frame(maxWidth: 150)
                        .foregroundColor(.white)
                        .background(Color.pink)
                        .cornerRadius(40)
                    }
                }
                NavigationLink(destination: DriverHome(), isActive: $driverSelected){
                    Button(action: {
                        self.driverSelected = true
                        customerSide = false
                    }) {
                        HStack {
                            Text("Driver")
                                //.fontWeight(.semibold)
                                .font(.title2)
                        }
                        .padding()
                        .frame(maxWidth: 150)
                        .foregroundColor(.white)
                        .background(Color.pink)
                        .cornerRadius(40)
                    }
                }
            }
        }
        
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
