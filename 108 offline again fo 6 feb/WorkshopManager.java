public class WorkshopManager {
    private Vehicle[] vehicles;
    private int vehicleCount;

    WorkshopManager() {
        vehicles = new Vehicle[1000];
        vehicleCount = 0;
    }

    public void addVehicle(Vehicle v) throws ServiceException {
        if (vehicleCount >= 1000) {
            throw new ServiceException("Cannot add more vehicles");
        }
        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i].getRegNum().equals(v.getRegNum())) {
                throw new ServiceException("Vehicle with registration number " + v.getRegNum() + " already exists");
            }
        }
        vehicles[vehicleCount++] = v;
    }

    public void displayVehicleDetails() {
        if (vehicleCount == 0) {
            System.out.println("No vehicles to display");
            return;
        }
        for (int i = 0; i < vehicleCount; i++) {
            vehicles[i].displayDetails();
            try {
                System.out.println("Service Cost: " + vehicles[i].calculateServiceCost());
            } catch (ServiceException e) {
                System.out.println("Service Cost: Error - " + e.getMessage());
            }
            System.out.println("-----------------------");
        }
    }

    public double calcTotalRevenue() {
        double total = 0;
        for (int i = 0; i < vehicleCount; i++) {
            try {
                total += vehicles[i].calculateServiceCost();
            } catch (ServiceException e) {
                System.out.println("Error calculating revenue for vehicle " + vehicles[i].getRegNum() + ": " + e.getMessage());
            }
        }
        return total;
    }
}