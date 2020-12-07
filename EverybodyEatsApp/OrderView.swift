//
//  OrderView.swift
//  ErryBody Eats
//
//  Created by Daniyal Khan on 11/15/20.
//

import Foundation
import SwiftUI
import CoreLocation
import MapKit


struct OrderView: View {
    var body: some View {
        VStack {
            
            MapView(coordinate: CLLocationCoordinate2D(
                        latitude: 39.2557,
                        longitude: -76.7110)
            )
                .edgesIgnoringSafeArea(.top)
                //.frame(height: 500)
            
            Text("Driver Location")
                .font(.title)
        }
    }
}

struct MapView: UIViewRepresentable {
    var coordinate: CLLocationCoordinate2D
    let annotation = MKPointAnnotation()
    
    func makeUIView(context: Context) -> MKMapView {
        MKMapView(frame: .zero)
    }
    

    func updateUIView(_ uiView: MKMapView, context: Context) {
        let span = MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01)
        annotation.coordinate = CLLocationCoordinate2D(latitude: coordinate.latitude, longitude: coordinate.longitude)
        uiView.addAnnotation(annotation)
        
        let region = MKCoordinateRegion(center: coordinate, span: span)
        uiView.setRegion(region, animated: true)
        
    }
}

struct OrderView_Previews: PreviewProvider {
    static var previews: some View {
        OrderView()
    }
}
