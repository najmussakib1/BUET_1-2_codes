class Truck extends Vehicle implements Serviceable {
    private double loadCapacity;
    private double serviceCost;
    private double maxServiceCost;

    Truck(String regNum, String ownerName, double baseServiceCost, double loadCapacity, double maxServiceCost) throws ServiceException {
        super(regNum, ownerName, baseServiceCost);
        this.loadCapacity = loadCapacity;
        this.maxServiceCost = maxServiceCost;
        if (maxServiceCost < 0) {
            throw new ServiceException("Max service cost cannot be negative");
        }
    }

    public double calculateServiceCost() throws ServiceException {
        serviceCost = getBaseServiceCost() + loadCapacity * 1000;
        if (serviceCost > maxServiceCost) {
            serviceCost = maxServiceCost;
            throw new ServiceException("Service cost exceeds maximum limit for truck");
        }
        return serviceCost;
    }

    public void doService() {
        System.out.println("Servicing truck with load capacity: " + loadCapacity);
        try {
             double sc = calculateServiceCost();
             System.out.println("Service completed. Cost: " + sc);
        } catch (ServiceException e) {
             System.out.println("Error servicing truck: " + e.getMessage());
        }
    }
}