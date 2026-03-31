public class Main {
    public static void main(String[] args) {
        WorkshopManager wm = new WorkshopManager();
        try {
            Vehicle c1 = new Car("Dhaka-01","Najmus Sakib",2000,4,10000);
            Vehicle c2 = new Car("Dhaka-02","Humayun Kabir",2000,4,10000);
            Vehicle c3 = new Car("Dhaka-03","Asfakul Kabir",2000,4,10000);
            Vehicle c4 = new Car("Dhaka-04","Nasima akter",2000,4,10000);
            Vehicle b1 = new Bike("Dhaka-05","Sakib",2000,150,5000);
            Vehicle b2 = new Bike("Dhaka-01","Kabir",2000,150,4000); // Duplicate add hobe na, exception throw hobe
            Vehicle t1 = new Truck("Dhaka-06","Sakib",2000,10,15000);
            wm.addVehicle(c1);
            wm.addVehicle(c2);
            wm.addVehicle(c3);
            wm.addVehicle(c4);
            wm.addVehicle(b1);
            wm.addVehicle(t1);
            wm.addVehicle(b2); // This will throw an exception due to duplicate registration number



        } catch (ServiceException se) {
            System.out.println("Error adding vehicle: " + se.getMessage());
        }

        wm.displayVehicleDetails();
        System.out.println("Total Revenue: " + wm.calcTotalRevenue());
        System.out.println("\n--- Performing Services ---");
        
        try {
            Serviceable s1 = new Car("KA05XY9876", "Alice", 4000, 2, 6000);
            s1.doService();
        } catch (ServiceException e) {
             System.out.println(e.getMessage());
        }
    }
}